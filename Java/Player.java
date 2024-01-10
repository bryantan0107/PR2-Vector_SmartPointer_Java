package a11930138;

import java.util.*;

public class Player implements Comparable <Player> {
    private String name;
    private Queue<VehicleCard> deck = new ArrayDeque();

    public Player(final String name) {
        if (name == null || name.isEmpty())
            throw new IllegalArgumentException("name should not be null or empty.");
        else
            this.name = name;
    }

    public String getName() {
        return name;
    }

    public int getScore() {
        int score=0;
        for (VehicleCard card : deck)
            score += card.totalBonus();
        return score;
    }

    public void addCards(final Collection<VehicleCard> cards) {
        if(cards == null)
            throw new IllegalArgumentException("cards arg can't be null");
        for(VehicleCard card : cards)
            addCard(card);
    }

    public void addCard(final VehicleCard card) {
        if(card == null)
            throw new IllegalArgumentException("the card can't be null");
        deck.add(card);
    }

    void clearDeck() {
        deck.clear();
    }

    public List<VehicleCard> getDeck() {
        List<VehicleCard> shallowDeck = new ArrayList<VehicleCard>(deck);
        return shallowDeck;
    }

    protected VehicleCard peekNextCard() {
        return deck.peek();
    }

    public VehicleCard playNextCard() {
        return deck.poll();
    }

    public int compareTo(final Player other) {
        return this.name.compareToIgnoreCase(other.name);
        //return Integer.compare(this.getScore(), other.getScore());
        //return String.CASE_INSENSITIVE_ORDER.compare(getName(), other.getName());

    }

    @Override
    public int hashCode() {
        return name.toLowerCase().hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        if(obj==null)
            return false;
        else
            return obj.hashCode() == this.hashCode();
    }

    @Override
    public String toString() {
        String ans = this.name + '(' + this.getScore() + "):\n";
        boolean first=false;
        for(VehicleCard d: deck) {
            if (!first)
                first = true;
            else
                ans += "\n";
            ans += d.toString();
        }
        return ans;
    }

    public boolean challengePlayer(Player p) {
        if(p==null || p.equals(this))
            throw new IllegalArgumentException("p should not be null or this.");

        List<VehicleCard> drawList = new ArrayList<VehicleCard>();
        List<VehicleCard> copyofthis = this.getDeck();
        List<VehicleCard> copyofp = p.getDeck();
        boolean draw = false;

        while(true){
            if(this.getDeck().size() == 0 || p.getDeck().size() == 0){
                if(draw){
                    this.clearDeck();
                    this.addCards(copyofthis);

                    p.clearDeck();
                    p.addCards(copyofp);
                    return false;
                }
                if(this.getDeck().size() == 0)
                    return false;
                return true;
            } else if (this.peekNextCard().totalBonus() < p.peekNextCard().totalBonus()) {
                if(draw){
                    p.addCards(drawList);
                    drawList.clear();
                    draw = false;
                }
                p.addCard(this.playNextCard());
                p.addCard(p.playNextCard());
            } else if (this.peekNextCard().totalBonus() > p.peekNextCard().totalBonus()) {
                if(draw){
                    this.addCards(drawList);
                    drawList.clear();
                    draw = false;
                }
                this.addCard(p.playNextCard());
                this.addCard(this.playNextCard());
            } else {
                drawList.add(this.playNextCard());
                drawList.add(p.playNextCard());
                draw = true;
            }
        }
    }

    public static Comparator<Player> compareByScore() {
//        return new Comparator<Player>() {
//            @Override
//            public int compare(Player p1, Player p2) {
//                return p1.getScore()  - p2.getScore();
//            }
//        };
        return Comparator.comparing(Player::getScore);
    }

    public static Comparator<Player> compareByDeckSize() {
//        return new Comparator<Player>() {
//            @Override
//            public int compare(Player p1, Player p2) {
//                return p1.getDeck().size()  - p2.getDeck().size();
//            }
//        };
        return Comparator.comparing(Player -> Player.getDeck().size());
    }

}
