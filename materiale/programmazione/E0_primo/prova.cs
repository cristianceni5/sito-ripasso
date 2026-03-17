public static class Prova
{
    double calcRadice(int numero)
    {
        return Math.Sqrt(numero);
    }

    public static void Main()
    {
        Console.ReadLine("Inserisci un numero per calcolare la radice quadrata: ");
        int radice = Convert.ToInt32(Console.ReadLine());
        double radiceCalcolare = calcRadice(radice);

        Console.WriteLine("La radice quadrata di {0} è: {1}", radice, radiceCalcolare);
    }
}