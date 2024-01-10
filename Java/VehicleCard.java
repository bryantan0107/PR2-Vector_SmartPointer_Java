package a11930138;

import java.util.*;

public class VehicleCard implements Comparable <VehicleCard > {
    public enum Category {
        ECONOMY_MPG("Miles/Galon"),
        CYLINDERS_CNT("Zylinder"),
        DISPLACEMENT_CCM("Hubraum[cc]"),
        POWER_HP("Leistung[hp]"),
        WEIGHT_LBS("Gewicht[lbs]") {@Override public boolean isInverted() {return true;}},
        ACCELERATION("Beschleunigung") {@Override public boolean isInverted() {return true;}},
        YEAR("Baujahr[19xx]");

        private final String categoryName;

        private Category(final String categoryName) {
            if (categoryName == null || categoryName.isEmpty())
                throw new IllegalArgumentException("categoryName should not be null or empty.");
            this.categoryName = categoryName;
        }

        public boolean isInverted() {
            return false;
        }

        public int bonus(final Double value) {
            if (isInverted()) {
                return (int) -value;
            }
            return (int) value.intValue();
        }

        @Override
        public String toString() {
            return categoryName;
        }
    }

    private String name;
    private Map<Category, Double> categories;

    public VehicleCard(final String name, final Map<Category, Double> categories) {
        if(name==null || name.isEmpty())
            throw new IllegalArgumentException("name should not be null or empty.");
        if(categories==null || !(categories.size()==7))
            throw new IllegalArgumentException("categories should not be null or categories should contain all Category values.");
        for (Double value : categories.values())
            if(value==null || value<=0)
                throw new IllegalArgumentException("categories should not contains any null value or values less than 0.");
        Map<Category, Double> shallowCopy = new EnumMap<Category, Double>(categories);

        this.name=name;
        this.categories=shallowCopy;
    }

    public String getName() {
        return name;
    }

    public Map<Category, Double> getCategories() {
        Map<Category, Double> shallowMap = new EnumMap<Category, Double>(this.categories);
        return shallowMap;
    }

    public static Map<Category, Double> newMap(double economy, double cylinders , double displacement , double power , double weight , double acceleration, double year) {
        Map<Category, Double> newMap = new EnumMap<Category, Double>(Category.class);

        newMap.put(Category.ECONOMY_MPG, economy);
        newMap.put(Category.CYLINDERS_CNT, cylinders);
        newMap.put(Category.DISPLACEMENT_CCM, displacement);
        newMap.put(Category.POWER_HP, power);
        newMap.put(Category.WEIGHT_LBS, weight);
        newMap.put(Category.ACCELERATION, acceleration);
        newMap.put(Category.YEAR, year);

        return newMap;
    }

    @Override
    public int compareTo(final VehicleCard other) {
        if(this.getName().compareTo(other.getName())==0)
            return Math.min(this.totalBonus(), other.totalBonus());
        else
            return this.getName().compareTo(other.getName());
    }

    public int totalBonus(){
        int summe = 0;
        for(var category : categories.entrySet())
            summe += category.getKey().bonus(category.getValue());
        return (int)summe;
    }

    @Override
    public int hashCode() {
        return name.hashCode() + totalBonus();
    }

    @Override
    public boolean equals(Object obj) {
        if(obj==null)
            return false;
        else
            return obj.hashCode()==hashCode();
    }

    @Override
    public String toString () {
        int first =  0;
        String ans = "- " + name + "(" + this.totalBonus() + ") -> {";
        for(Category c : categories.keySet()){
            if(first == 0)
                ans += (c.toString() + "=" + categories.get(c));
            else
                ans += (", " + c.toString() + "=" + categories.get(c));
            first++;
        }
        ans += "}";
        return ans;
    }
}