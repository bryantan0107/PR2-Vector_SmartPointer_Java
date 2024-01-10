package a11930138;

import java.util.*;

public class FoilVehicleCard extends VehicleCard {

    private Set<Category> specials;

    public FoilVehicleCard(final String name, final Map<Category, Double> categories,final Set<Category> specials) {
        super(name, categories);
        if(specials==null || specials.size()>2 || specials.isEmpty())
            throw new IllegalArgumentException("specials should not contains more than 3 items or be null or empty.");

        this.specials = new HashSet<Category>(specials);
    }

    public Set<Category> getSpecials() {
        Set<Category> shallowCopy = new HashSet<Category>(specials);
        return shallowCopy;
    }

    @Override
    public int totalBonus(){
        Map<Category, Double> copyofvc = getCategories();
        int summe=0;
        summe += super.totalBonus();
        for(Category category : specials){
            summe += copyofvc.get(category);
        }
        return summe;
    }

    @Override
    public String toString(){
        Map<Category, Double> copyofvc = getCategories();
        String ans = "- " + this.getName() + "(" + this.totalBonus() + ") -> {";
        boolean first=false;
        for (var c : copyofvc.entrySet()) {
            if (!first)
                first = true;
            else
                ans += ", ";
            if(specials.contains(c.getKey())){
                ans += ('*' + c.getKey().toString() + "*=" + c.getValue());
            }else{
                ans += (c.getKey().toString() + "=" + c.getValue());
            }
        }
        ans+= "}";
        return ans;
    }
}
